# get_fw_rules.ps1
$rules = @("Block_http_conn", "Allow_rdp_conn", "Block_ftp_conn", "Block_ping_conn")

$result = foreach ($ruleName in $rules) {
    $rule = Get-NetFirewallRule -DisplayName $ruleName -ErrorAction SilentlyContinue
    if ($rule) {
        [PSCustomObject]@{
            Name      = $rule.DisplayName
            Enabled   = $rule.Enabled
            Direction = $rule.Direction
            Action    = $rule.Action
            Profile   = $rule.Profile -join ", "
        }
    }
}

$result | Format-Table -AutoSize
$result | Format-Table -AutoSize | Out-File -FilePath "result.txt" -Encoding UTF8